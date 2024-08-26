import Foundation
import Combine

class SensorDataModel: ObservableObject {
    @Published var acceleration: (x: Double, y: Double, z: Double) = (0.0, 0.0, 0.0)
    @Published var gyro: (x: Double, y: Double, z: Double) = (0.0, 0.0, 0.0)
    @Published var batteryLevel: Double = 100.0

    private var timer: Timer?
    private let updateInterval: TimeInterval = 1.0

    init() {
        startSimulatingData()
    }

    func startSimulatingData() {
        timer = Timer.scheduledTimer(withTimeInterval: updateInterval, repeats: true) { [weak self] _ in
            self?.generateRandomData()
        }
    }

    private func generateRandomData() {
        acceleration = (x: Double.random(in: -10...10), y: Double.random(in: -10...10), z: Double.random(in: -10...10))
        gyro = (x: Double.random(in: -5...5), y: Double.random(in: -5...5), z: Double.random(in: -5...5))
        batteryLevel = Double.random(in: 20...100) // 模擬電量數據
    }
}
