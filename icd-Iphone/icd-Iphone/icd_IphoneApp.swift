import SwiftUI
@main
struct MyApp: App {
    @State private var isShowingLaunchScreen = true

    var body: some Scene {
        WindowGroup {
            ZStack {
                ContentView()
                if isShowingLaunchScreen {
                    LaunchScreenView(isShowing: $isShowingLaunchScreen)
                        .onAppear {
                            DispatchQueue.main.asyncAfter(deadline: .now() + 2) {
                                withAnimation {
                                    isShowingLaunchScreen = false
                                }
                            }
                        }
                }
            }
        }
    }
}
