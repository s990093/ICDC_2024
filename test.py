import asyncio
import websockets
import json
import time
import serial
from datetime import datetime, timedelta

# 配置串口参数
ser = serial.Serial('/dev/cu.usbserial-110', 115200)  # 修改为你 Arduino 所连接的串口端口和波特率

async def websocket_test():
    ip = "49.213.238.75"
    uri = f"ws://{ip}:8000/ws/chat/example_room/"  # WebSocket 服务器的完整路径
    
    async with websockets.connect(uri) as websocket:
        print("Connected to WebSocket server. You can start sending messages.")
        
        
        try:
            while True:
                if ser.in_waiting > 0:
                    # 读取 Arduino 发送的串口数据
                    arduino_data = ser.readline().decode('utf-8').strip()
                    # print(arduino_data)
                    
                    # 判断并解析数据
                    if arduino_data == "action: true":
                        
                        # 检查是否已经过了 20 秒
                        user = "eps32"
                        message = "Hello"
                        action_code = "123"
                        
                        # 构建 JSON 数据
                        data = {
                            "user": user,
                            "message": message,
                            "action_code": action_code
                        }
                        
                        # 发送消息到 WebSocket 服务器
                        await websocket.send(json.dumps(data))
                        print(f"Sent _>>>>>>>>")
                        
                        
                        # 接收服务器的响应
                        # response = await websocket.recv()
                        # print(f"Received: {response}")
                    
                await asyncio.sleep(1)  # 使用 asyncio.sleep 替代 time.sleep，以确保协程正确运行
        
        except websockets.exceptions.ConnectionClosed as e:
            print(f"WebSocket connection closed: {e}")
        except Exception as e:
            print(f"An error occurred: {e}")

# 执行 WebSocket 测试
asyncio.get_event_loop().run_until_complete(websocket_test())
