import SwiftUI

struct CollisionView: View {
    @State private var collisionDetected = false
    @StateObject private var webSocketManager = WebSocketManager()
    private let speechManager = SpeechManager() // Instantiate SpeechManager
    @State private var isPulsating = false // State variable to control pulsating

    
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
                .scaleEffect(webSocketManager.collisionDetected ? 1.2 : 1.0) // Base scale effect
                .opacity(webSocketManager.collisionDetected ? 1.0 : 0.8) // Base fade effect
                .pulsating(isActive: $isPulsating) // Apply the custom pulsating effect
                .onChange(of: webSocketManager.collisionDetected) { newValue in
                    if newValue {
                        // Activate pulsating animation
                        isPulsating = true
                        
                        // Speak when collision is detected
                        speechManager.speak(text: "Detection of tilt Please adjust quickly")
                        
                        // Reset the collisionDetected state and stop pulsating after 3 seconds
                        DispatchQueue.main.asyncAfter(deadline: .now() + 3) {
                            webSocketManager.collisionDetected = false
                            isPulsating = false
                        }
                    }
                }
            
            
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
        //        .onChange(of: webSocketManager.collisionDetected) { newValue in
        //                   if newValue {
        //                       // Speak when collision is detected
        //                       speechManager.speak(text: "The food box is tilted. Please adjust it quickly.")
        //
        //                       // Reset the collisionDetected state after 3 seconds
        //                       DispatchQueue.main.asyncAfter(deadline: .now() + 3) {
        //                           webSocketManager.collisionDetected = false
        //                       }
        //                   }
        //               }
        .padding()
        .onDisappear {
            webSocketManager.disconnect() // Ensure disconnection when the view disappears
        }
    }
    
}
