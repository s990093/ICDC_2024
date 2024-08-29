import asyncio
import websockets
import json
from rich.console import Console

# Create a rich Console instance
console = Console()

async def send_message():
    ip = "49.213.238.75"
    uri = f"ws://{ip}:8000/ws/chat/example_room/"  # WebSocket server's full path
    
    async with websockets.connect(uri) as websocket:
        console.print("Connected to WebSocket server.", style="bold green")
        
        try:
            # Construct JSON data to send to WebSocket server
            data = {
                "user": "eps32",
                "message": "Hello",
                "action_code": "123"
            }
            
            # Send message to WebSocket server
            await websocket.send(json.dumps(data))
            console.print(f"Message sent: {data}", style="bold blue")
        
        except websockets.exceptions.ConnectionClosed as e:
            console.print(f"WebSocket connection closed: {e}", style="bold red")
        except Exception as e:
            console.print(f"An error occurred: {e}", style="bold red")

# Execute the message sending function
asyncio.get_event_loop().run_until_complete(send_message())
