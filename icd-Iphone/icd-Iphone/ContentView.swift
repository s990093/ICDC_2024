import SwiftUI

struct ContentView: View {

    var body: some View {
        TabView {
            CollisionView()
                .tabItem {
                    Image(systemName: "bolt.fill")
                }

            BatteryView()
                .tabItem {
                    Image(systemName: "battery.100")
                }

            EnvironmentView()
                .tabItem {
                    Image(systemName: "thermometer.sun.fill")
                }
        }
//        .preferredColorScheme(settings.isDarkMode ? .dark : .light) // Set color scheme based on the toggle
    }
}


#Preview {
    ContentView()
}
