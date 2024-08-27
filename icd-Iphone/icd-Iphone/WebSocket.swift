import SwiftUI
import Combine

class WebSocketManager: ObservableObject {
    private var webSocketTask: URLSessionWebSocketTask?
    @Published var receivedMessage: String = ""
    @Published var isConnected: Bool = false
    @Published var collisionDetected: Bool = false
    var ip = "49.213.238.75"
    
    init() {
        connect() // Automatically connect when the manager is initialized
    }
    
    func connect() {
        let url = URL(string: "ws://49.213.238.75:8000/ws/chat/example_room/")!
        webSocketTask = URLSession.shared.webSocketTask(with: url)
        webSocketTask?.resume()
        isConnected = true
        listenForMessages()  // Start listening for messages
    }
    
    func disconnect() {
        webSocketTask?.cancel(with: .goingAway, reason: nil)
        isConnected = false
    }
    
    func send(user: String, message: String, actionCode: String) async {
        self.connect()
        let data: [String: String] = [
            "user": user,
            "message": message,
            "action_code": actionCode
        ]
        
        if let jsonData = try? JSONSerialization.data(withJSONObject: data, options: []) {
            let message = URLSessionWebSocketTask.Message.data(jsonData)
            do {
                try await webSocketTask?.send(message)
                print("Sent: \(data)")
            } catch {
                print("WebSocket sending error: \(error)")
            }
        }
    }
    
    private func listenForMessages() {
        webSocketTask?.receive { [weak self] result in
            switch result {
            case .failure(let error):
                print("WebSocket receiving error: \(error)")
            case .success(let message):
                switch message {
                case .data(let data):
                    if let messageString = String(data: data, encoding: .utf8) {
                        self?.handleReceivedMessage(messageString)
                    }
                case .string(let text):
                    self?.handleReceivedMessage(text)
                @unknown default:
                    break
                }
                // Continue listening for more messages
                self?.listenForMessages()
            }
        }
    }
    
    private func handleReceivedMessage(_ message: String) {
        // Parse the message
        if let data = message.data(using: .utf8),
           let json = try? JSONSerialization.jsonObject(with: data, options: []) as? [String: String],
           let actionCode = json["action_code"] {
            print(actionCode)
            // Check for a specific action code
            if actionCode == "123" {
                DispatchQueue.main.async {
                    self.collisionDetected = true
                }
            }
            print("Received message: \(message)")
        }
    }
    
    func send_motor(user: String, x: Double, y: Double) async {
        self.connect()
        
        var actionCode = ""
        
        // Determine the action code based on x and y values
        if x > 0 {
            actionCode = x > 0 ? "10" : "11" // Example logic, modify based on actual requirements
        } else if x < 0 {
            actionCode = x < 0 ? "11" : "10" // Example logic, modify based on actual requirements
        }
        
        if y > 0 {
            actionCode = y > 0 ? "12" : "13" // Example logic, modify based on actual requirements
        } else if y < 0 {
            actionCode = y < 0 ? "13" : "12" // Example logic, modify based on actual requirements
        }
        
        // Create the data dictionary
        let data: [String: String] = [
            "user": user,
            "message": "Control Command",
            "action_code": actionCode
        ]
        
        // Convert the data dictionary to JSON
        if let jsonData = try? JSONSerialization.data(withJSONObject: data, options: []) {
            let message = URLSessionWebSocketTask.Message.data(jsonData)
            do {
                try await webSocketTask?.send(message)
                print("Sent: \(data)")
            } catch {
                print("WebSocket sending error: \(error)")
            }
        }
    }

}
