import SwiftUI
import UIKit

struct GIFView: UIViewRepresentable {
    let gifName: String

    func makeUIView(context: Context) -> UIView {
        let view = UIView(frame: .zero)
        
        let gifImageView = UIImageView()
        gifImageView.contentMode = .scaleAspectFit
        gifImageView.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(gifImageView)

        NSLayoutConstraint.activate([
            gifImageView.topAnchor.constraint(equalTo: view.topAnchor),
            gifImageView.bottomAnchor.constraint(equalTo: view.bottomAnchor),
            gifImageView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            gifImageView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
        ])

        if let path = Bundle.main.path(forResource: gifName, ofType: "gif"),
           let data = try? Data(contentsOf: URL(fileURLWithPath: path)) {
            let gifImage = UIImage.gif(data: data)
            gifImageView.image = gifImage
        }

        return view
    }

    func updateUIView(_ uiView: UIView, context: Context) {}
}

// Extension to load GIF
extension UIImage {
    static func gif(data: Data) -> UIImage? {
        let source = CGImageSourceCreateWithData(data as CFData, nil)
        guard let source = source else { return nil }
        return UIImage.animatedImageWithSource(source)
    }

    static func animatedImageWithSource(_ source: CGImageSource) -> UIImage? {
        let count = CGImageSourceGetCount(source)
        var images = [UIImage]()
        var duration: Double = 0

        for i in 0..<count {
            if let image = CGImageSourceCreateImageAtIndex(source, i, nil) {
                images.append(UIImage(cgImage: image))
            }

            let frameDuration = UIImage.gifFrameDuration(source, index: i)
            duration += frameDuration
        }

        return UIImage.animatedImage(with: images, duration: duration)
    }

    static func gifFrameDuration(_ source: CGImageSource, index: Int) -> Double {
        let frameProperties = CGImageSourceCopyPropertiesAtIndex(source, index, nil) as? [String: Any]
        let gifProperties = frameProperties?[kCGImagePropertyGIFDictionary as String] as? [String: Any]
        
        let delayTime = gifProperties?[kCGImagePropertyGIFUnclampedDelayTime as String] as? Double
        let defaultDelay = 0.1
        
        return delayTime ?? defaultDelay
    }
}
