struct ContentView: View {
    @EnvironmentObject var settings: AppSettings

    var body: some View {
        NavigationView {
            VStack {
                List {
                    NavigationLink(destination: CollisionView()) {
                        Label("碰撞檢測", systemImage: "bolt.fill")
                            .padding()
                            .background(Color.accentColor.opacity(0.2))
                            .cornerRadius(10)
                    }
                    
                    NavigationLink(destination: BatteryView()) {
                        Label("ESP32 電量", systemImage: "battery.100")
                            .padding()
                            .background(Color.accentColor.opacity(0.2))
                            .cornerRadius(10)
                    }
                }
                .listStyle(InsetGroupedListStyle())
                
                Toggle(isOn: $settings.isDarkMode) {
                    Text("切換到夜間模式")
                        .font(.title2)
                        .padding()
                }
                .toggleStyle(SwitchToggleStyle(tint: Color.accentColor))
            }
            .navigationTitle("主頁面")
            .navigationBarTitleDisplayMode(.large)
        }
        .preferredColorScheme(settings.isDarkMode ? .dark : .light)
    }
}
