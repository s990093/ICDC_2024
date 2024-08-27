import SwiftUI

struct CollisionView: View {
    @State private var collisionDetected = false
    @StateObject private var webSocketManager = WebSocketManager()
    
    var body: some View {
        VStack {
            
            // Title at the top
            Text("Collision detection")
                .font(.largeTitle)
                .fontWeight(.bold)
                .padding(.top, 30)
                .padding(.bottom, 20)
                .foregroundColor(.primary)
            
            Spacer()
            
            // Collision status text with animation
            Text(webSocketManager.collisionDetected ? "Detection!" : "No detection!")
                .font(.title2)
                .fontWeight(.semibold)
                .foregroundColor(webSocketManager.collisionDetected ? .red : .green)
                .padding()
                .background(webSocketManager.collisionDetected ? Color.red.opacity(0.2) : Color.green.opacity(0.2))
                .cornerRadius(10)
                .shadow(radius: 5)
                .scaleEffect(webSocketManager.collisionDetected ? 1.2 : 1.0) // Scale effect for animation
                .opacity(webSocketManager.collisionDetected ? 1.0 : 0.8) // Fade effect for animation
                .animation(.easeInOut(duration: 0.5), value: webSocketManager.collisionDetected) // Animation applied to changes in collisionDetected
            
            Spacer()
            
            // Button with animation
//            Button(action: {
//                withAnimation {
//                    collisionDetected.toggle()
//                }
//            }) {
//                Text("Check detection")
//                    .font(.title2)
//                    .padding()
//                    .background(Color.blue)
//                    .foregroundColor(.white)
//                    .cornerRadius(12)
//                    .shadow(radius: 10)
//            }
//            .padding(.top, 20)
        }
        .padding()
        .onDisappear {
            webSocketManager.disconnect() // Ensure disconnection when the view disappears
        }
    }
    
}
