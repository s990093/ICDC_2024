import SwiftUI

struct PulsatingEffect: ViewModifier {
    @Binding var isActive: Bool
    
    func body(content: Content) -> some View {
        content
            .scaleEffect(isActive ? 1.2 : 1.0) // Scale effect
            .animation(Animation.easeInOut(duration: 0.5).repeatCount(3, autoreverses: true), value: isActive) // Pulsating effect
    }
}

extension View {
    func pulsating(isActive: Binding<Bool>) -> some View {
        self.modifier(PulsatingEffect(isActive: isActive))
    }
}
