import SwiftUI

struct LaunchScreenView: View {
    @Binding var isShowing: Bool
    
    @State private var backgroundColor: Color = Color.blue
    @State private var scale: CGFloat = 0.5
    @State private var rotation: Double = 0
    @State private var textOffset: CGFloat = -100 // 初始文字位置
    
    var body: some View {
        ZStack {
            // 背景顏色變化動畫
            backgroundColor
                .ignoresSafeArea()
                .animation(Animation.linear(duration: 3).repeatForever(autoreverses: true), value: backgroundColor)
                .onAppear {
                    backgroundColor = Color.cyan
                }
            
            VStack {
                // 運送貨物圖標動畫
                Image(systemName: "truck.fill")
                    .font(.system(size: 100))
                    .foregroundColor(.white)
                    .scaleEffect(scale)
                    .rotationEffect(.degrees(rotation))
                    .opacity(isShowing ? 1 : 0)
                    .animation(.easeInOut(duration: 1.5), value: isShowing)
                    .onAppear {
                        // 設定縮放和旋轉動畫
                        withAnimation(Animation.easeInOut(duration: 1.5).repeatForever(autoreverses: true)) {
                            scale = 1.0
                            rotation = 360
                        }
                    }
                
                // 移動的文字
                Text("SeaSaw")
                    .font(.largeTitle)
                    .foregroundColor(.white)
                    .opacity(isShowing ? 1 : 0)
                    .padding()
                    .background(Color.black.opacity(0.5))
                    .cornerRadius(10)
                    .shadow(radius: 10)
                    .offset(y: textOffset)
                    .animation(.easeInOut(duration: 1.5), value: textOffset)
                    .onAppear {
                        // 設定文字移動動畫
                        withAnimation(Animation.easeInOut(duration: 1.5)) {
                            textOffset = 0
                        }
                    }
                
                Spacer()
            }
        }
        .onAppear {
            // 當啟動畫面出現時，設置顏色變化動畫
            DispatchQueue.main.asyncAfter(deadline: .now() + 2) {
                withAnimation {
                    isShowing = false
                }
            }
        }
    }
}
