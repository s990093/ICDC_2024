import SwiftUI

struct EnvironmentView: View {
    @State private var temperature: Double = 22.0 // 假設默認溫度為 22°C
    @State private var humidity: Double = 50.0 // 假設默認濕度為 50%

    var body: some View {
        VStack(spacing: 20) {
            Text("Environmental monitoring")
                .font(.largeTitle)
                .fontWeight(.bold)
                .padding()
                .background(Color.accentColor)
                .foregroundColor(.white)
                .cornerRadius(10)
            
            VStack(alignment: .leading, spacing: 15) {
                HStack {
                    Image(systemName: "thermometer")
                        .foregroundColor(.accentColor)
                    
                    Text("Urrent temperature: \(temperature, specifier: "%.1f")°C")
                        .font(.title2)
                        .padding()
                        .background(temperature > 30 ? Color.red.opacity(0.2) : Color.blue.opacity(0.2))
                        .cornerRadius(10)
                }
                .transition(.slide)
                .animation(.easeInOut(duration: 0.5))

                HStack {
                    Image(systemName: "drop.fill")
                        .foregroundColor(.accentColor)
                    
                    Text("Current humidity: \(humidity, specifier: "%.1f")%")
                        .font(.title2)
                        .padding()
                        .background(humidity > 70 ? Color.blue.opacity(0.2) : Color.green.opacity(0.2))
                        .cornerRadius(10)
                }
                .transition(.slide)
                .animation(.easeInOut(duration: 0.5))
            }
            
            Button(action: {
                // 模擬更新溫度和濕度數據
                withAnimation {
                    temperature = Double.random(in: 15...35)
                    humidity = Double.random(in: 30...90)
                }
            }) {
                Text("Update data")
                    .font(.title2)
                    .padding()
                    .background(Color.blue)
                    .foregroundColor(.white)
                    .cornerRadius(10)
                    .shadow(radius: 5)
            }
        }
        .padding()
        .background(Color.gray.opacity(0.1))
        .cornerRadius(20)
        .shadow(radius: 10)
        .transition(.opacity)
        .animation(.easeInOut(duration: 0.5))
    }
}
