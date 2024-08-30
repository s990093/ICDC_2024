import SwiftUI

struct CollisionView: View {
    @StateObject private var webSocketManager = WebSocketManager()
    private let speechManager = SpeechManager() // Instantiate SpeechManager
    @State private var isPulsating = false // State variable to control pulsating
    
    var body: some View {
        VStack {
            // Title at the top
            Text("Collision Detection")
                .font(.system(size: 36, weight: .bold))
                .padding(.top, 30)
                .padding(.bottom, 20)
                .foregroundColor(.primary)
            
            Spacer()
            
            // Collision status text with enhanced animation
            Text(webSocketManager.collisionDetected ? "Collision Detected!" : "No Collision")
                .font(.system(size: 48, weight: .heavy))
                .foregroundColor(webSocketManager.collisionDetected ? .red : .green)
                .padding()
                .background(webSocketManager.collisionDetected ? Color.red.opacity(0.3) : Color.green.opacity(0.3))
                .cornerRadius(15)
                .shadow(color: webSocketManager.collisionDetected ? .red : .green, radius: 10, x: 0, y: 0)
                .scaleEffect(webSocketManager.collisionDetected ? 1.2 : 1.0) // Increased scale effect
                .opacity(webSocketManager.collisionDetected ? 1.0 : 0.8) // Base fade effect
                .pulsating(isActive: $isPulsating) // Apply the custom pulsating effect
                .onChange(of: webSocketManager.collisionDetected) { newValue in
                    if newValue {
                        // Activate pulsating animation
                        isPulsating = true
                        
                        // Speak when collision is detected
                        speechManager.speak(text: "動きが検出されました")
                        
                        // Reset the collisionDetected state and stop pulsating after 3 seconds
                        DispatchQueue.main.asyncAfter(deadline: .now() + 3) {
                            webSocketManager.collisionDetected = false
                            isPulsating = false
                        }
                    }
                }
            
            Spacer()
        }
        .padding()
        .onDisappear {
            webSocketManager.disconnect() // Ensure disconnection when the view disappears
        }
    }
}

