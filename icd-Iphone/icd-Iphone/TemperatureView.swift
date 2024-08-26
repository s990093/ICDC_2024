import SwiftUI

struct TemperatureView: View {
    @State private var temperature: Double = 22.0 // 假設默認溫度為 22°C

    var body: some View {
        VStack {
            Text("檢測溫度")
                .font(.largeTitle)
                .padding()

            Text("當前溫度: \(temperature, specifier: "%.1f")°C")
                .font(.title)
                .padding()
                .foregroundColor(temperature > 30 ? .red : .blue)

            // 假設您會在這裡有一個實際的溫度傳感器數據更新邏輯
            Button(action: {
                // 模擬更新溫度數據
                temperature = Double.random(in: 15...35)
            }) {
                Text("更新溫度")
                    .font(.title2)
                    .padding()
                    .background(Color.blue)
                    .foregroundColor(.white)
                    .cornerRadius(10)
            }
        }
        .padding()
        .background(Color.gray.opacity(0.1))
        .cornerRadius(20)
        .shadow(radius: 10)
    }
}
