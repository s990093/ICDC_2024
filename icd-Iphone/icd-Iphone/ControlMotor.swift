import SwiftUI
import Combine

struct ControlMotor: View {
    @State private var xAxis: Double = 0.0
    @State private var yAxis: Double = 0.0
    @ObservedObject private var webSocketManager = WebSocketManager()
    
    // Debounce settings
    private let debounceInterval: TimeInterval = 0.3
    @State private var debounceTimer: Timer?
    
    var body: some View {
        VStack(spacing: 20) {
            Text("Control ESP32")
                .font(.largeTitle)
                .fontWeight(.bold)
                .padding()
                .background(Color.accentColor)
                .foregroundColor(.white)
                .cornerRadius(10)

            // X Axis Control
            VStack {
                Text("X Axis: \(xAxis, specifier: "%.1f")")
                    .font(.title2)
                Slider(value: $xAxis, in: -100...100, step: 1)
                    .padding()
                    .onChange(of: xAxis) { newValue in
                        debounceSendControlSignal()
                    }
            }
            
            // Y Axis Control
            VStack {
                Text("Y Axis: \(yAxis, specifier: "%.1f")")
                    .font(.title2)
                Slider(value: $yAxis, in: -100...100, step: 1)
                    .padding()
                    .onChange(of: yAxis) { newValue in
                        debounceSendControlSignal()
                    }
            }
            
            Spacer()
        }
        .padding()
        .background(Color.gray.opacity(0.1))
        .cornerRadius(20)
        .shadow(radius: 10)
    }
    
    private func debounceSendControlSignal() {
        debounceTimer?.invalidate() // Invalidate the previous timer
        
        debounceTimer = Timer.scheduledTimer(withTimeInterval: debounceInterval, repeats: false) { _ in
            Task {
                await sendControlSignal()
            }
        }
    }
    
    private func sendControlSignal() async {
        await webSocketManager.send_motor(user: "iphone", x: xAxis, y: yAxis)
    }
}

#Preview {
    ControlMotor()
}
