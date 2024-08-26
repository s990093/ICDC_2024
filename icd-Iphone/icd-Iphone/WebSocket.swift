import SwiftUI
import Combine

class WebSocketManager: ObservableObject {
    private var webSocketTask: URLSessionWebSocketTask?
    @Published var receivedMessage: String = ""
    @Published var isConnected: Bool = false
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
                        DispatchQueue.main.async {
                            self?.receivedMessage = messageString
                            print("Received message: \(messageString)")
                        }
                    }
                case .string(let text):
                    DispatchQueue.main.async {
                        self?.receivedMessage = text
                        print("Received message: \(text)")
                    }
                @unknown default:
                    break
                }
                // Continue listening for more messages
                self?.listenForMessages()
            }
        }
    }
}
