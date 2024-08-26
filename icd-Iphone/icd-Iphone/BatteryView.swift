import SwiftUI

struct BatteryView: View {
    @State private var batteryLevel: Double = 100.0
    
    var body: some View {
        VStack {
            // Title at the top
            Text("ESP32 Power")
                .font(.largeTitle)
                .fontWeight(.bold)
                .padding(.top, 30)
                .padding(.bottom, 20)
                .foregroundColor(.primary)
            
            Spacer()
            
            // Battery level text with animation
            Text("Power: \(batteryLevel, specifier: "%.1f")%")
                .font(.title2)
                .fontWeight(.semibold)
                .foregroundColor(batteryLevel < 30 ? .red : .green)
                .padding()
                .background(batteryLevel < 30 ? Color.red.opacity(0.2) : Color.green.opacity(0.2))
                .cornerRadius(10)
                .shadow(radius: 5)
                .scaleEffect(batteryLevel < 30 ? 1.1 : 1.0) // Scale effect for animation
                .opacity(batteryLevel < 30 ? 1.0 : 0.8) // Fade effect for animation
                .animation(.easeInOut(duration: 0.5), value: batteryLevel) // Animation applied to changes in batteryLevel
            
            Spacer()
            
            // ProgressView for battery level
            ProgressView(value: batteryLevel, total: 100)
                .progressViewStyle(LinearProgressViewStyle())
                .padding()
                .frame(width: 200)
                .background(Color.white)
                .cornerRadius(10)
                .shadow(radius: 5)
            
            Spacer()
        }
        
    }
}
