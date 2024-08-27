import asyncio
import websockets
import json
import serial
from datetime import datetime, timedelta
from rich.console import Console
from rich.text import Text

# Configure serial connection to ESP32
ser = serial.Serial('/dev/cu.usbserial-130', 115200)

# Initialize rich console
console = Console()

async def handle_websocket(websocket):
    """ Handle WebSocket connection and communication. """
    console.print("Connected to WebSocket server.", style="bold green")
    
    last_sent_time = None  # Track the time when the last message was sent

    try:
        while True:
            if ser.in_waiting > 0:
                # Read data from Arduino
                arduino_data = ser.readline().decode('utf-8').strip()
                
                # Print received Arduino data
                console.print(f"Received from Arduino: {arduino_data}", style="bold blue")
                
                # Check and parse data
                if arduino_data == "action: true":
                    now = datetime.now()
                    
                    # Send message only if 20 seconds have passed since the last message
                    if last_sent_time is None or (now - last_sent_time) >= timedelta(seconds=20):
                        last_sent_time = now  # Update last sent time
                        
                        # Construct JSON data to send to WebSocket server
                        data = {
                            "user": "eps32",
                            "message": "Hello",
                            "action_code": "123"
                        }
                        
                        # Send message to WebSocket server
                        await websocket.send(json.dumps(data))
                        console.print(f"Sent data: {data}", style="bold green")
                    
            # Receive and print messages from the WebSocket server
            try:
                message = await websocket.recv()
                console.print(Text(message, style="bold yellow"))
            except websockets.exceptions.ConnectionClosed as e:
                console.print(f"WebSocket connection closed: {e}", style="bold red")
                break  # Exit the loop if the connection is closed

            await asyncio.sleep(1)  # Non-blocking sleep to allow other tasks to run
            
    except Exception as e:
        console.print(f"An error occurred: {e}", style="bold red")

async def websocket_test():
    """ Establish WebSocket connection and handle communication. """
    ip = "49.213.238.75"
    uri = f"ws://{ip}:8000/ws/chat/example_room/"  # WebSocket server URL
    
    async with websockets.connect(uri) as websocket:
        await handle_websocket(websocket)

# Run the WebSocket test
asyncio.run(websocket_test())
