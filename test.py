import asyncio
import websockets
import json
import time

async def websocket_test():
    uri = "ws://localhost:8000/ws/chat/example_room/"  # WebSocket 伺服器的完整路徑
    
    async with websockets.connect(uri) as websocket:
        print("Connected to WebSocket server. You can start sending messages.")
        
        try:
            while True:
                # 從用戶獲取輸入
                user = "eps32"
                message = "Hello"
                action_code = "123"
                
                # 構建 JSON 資料
                data = {
                    "user": user,
                    "message": message,
                    "action_code": action_code
                }
                
                # 傳送訊息到 WebSocket 伺服器
                await websocket.send(json.dumps(data))
                print(f"Sent: {data}")
                
                # 接收伺服器的回應
                response = await websocket.recv()
                print(f"Received: {response}")
                
                time.sleep(1)  # ���停 1 秒
        
        except websockets.exceptions.ConnectionClosed as e:
            print(f"WebSocket connection closed: {e}")
        except Exception as e:
            print(f"An error occurred: {e}")

# 執行 WebSocket 測試
asyncio.get_event_loop().run_until_complete(websocket_test())
