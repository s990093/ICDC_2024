import SwiftUI

struct TestWebSocketView: View {
    @StateObject private var webSocketManager = WebSocketManager()
      
      var body: some View {
          VStack {
              // Title
              Text("WebSocket Messages")
                  .font(.headline)
                  .padding(.top, 20)
              
              // Received messages display
              ScrollView {
                  Text(webSocketManager.receivedMessage)
                      .padding()
                      .background(Color.gray.opacity(0.1))
                      .cornerRadius(10)
                      .frame(maxWidth: .infinity, alignment: .leading)
              }
              .padding()
              
              // Send message button
              Button(action: {
                  Task {
                      await webSocketManager.send(user: "iphone", message: "Hello, World!", actionCode: "123")
                  }
              }) {
                  Text("Send Test Message")
                      .font(.title2)
                      .padding()
                      .background(Color.blue)
                      .foregroundColor(.white)
                      .cornerRadius(10)
              }
              .padding(.bottom, 20)
          }
          .padding()

          .onDisappear {
              webSocketManager.disconnect() // Ensure disconnection when the view disappears
          }
      }
}
