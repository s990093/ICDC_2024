import asyncio
import websockets
from rich.console import Console
from rich.text import Text

# 创建 rich 的 Console 实例
console = Console()

async def listen_for_messages():
    ip = "49.213.238.75"
    uri = f"ws://{ip}:8000/ws/chat/example_room/"  # WebSocket 服务器的完整路径
    
    async with websockets.connect(uri) as websocket:
        console.print("Connected to WebSocket server.", style="bold green")
        
        try:
            while True:
                # 接收来自服务器的消息
                message = await websocket.recv()
                
                # 使用 rich 打印消息
                console.print(Text(message, style="bold yellow"))
        
        except websockets.exceptions.ConnectionClosed as e:
            console.print(f"WebSocket connection closed: {e}", style="bold red")
        except Exception as e:
            console.print(f"An error occurred: {e}", style="bold red")

# 执行 WebSocket 监听
asyncio.get_event_loop().run_until_complete(listen_for_messages())
