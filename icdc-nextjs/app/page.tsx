// pages/index.js
import Head from "next/head";

export default function Home() {
  return (
    <div className="min-h-screen flex flex-col items-center p-4">
      <main className="flex flex-col items-center flex-1 w-full max-w-4xl mx-auto">
        <h1 className="text-4xl font-bold mb-8">Product Presentation</h1>

        <section className="w-full mb-8">
          <h2 className="text-2xl font-semibold">1. Project Goals</h2>
          <p className="mt-2">Describe the goals of the project here.</p>
        </section>

        <section className="w-full mb-8">
          <h2 className="text-2xl font-semibold">2. Market Analysis</h2>
          <p className="mt-2">Provide details on the market analysis here.</p>
        </section>

        <section className="w-full mb-8">
          <h2 className="text-2xl font-semibold">3. Marketing Strategy</h2>
          <p className="mt-2">Explain your marketing strategy here.</p>
        </section>

        <section className="w-full mb-8">
          <h2 className="text-2xl font-semibold">4. Project Progress</h2>
          <p className="mt-2">
            Outline the current progress of the project here.
          </p>
        </section>

        <section className="w-full mb-8">
          <h2 className="text-2xl font-semibold">5. Cost</h2>
          <p className="mt-2">Detail the cost aspects here.</p>
        </section>

        <section className="w-full mb-8">
          <h2 className="text-2xl font-semibold">6. Advertising Methods</h2>
          <p className="mt-2">Discuss the advertising methods here.</p>
        </section>

        <section className="w-full mb-8">
          <h2 className="text-2xl font-semibold">
            7. How to Deliver to the Customer
          </h2>
          <p className="mt-2">
            Explain the delivery process to the customer here.
          </p>
        </section>

        <section className="w-full mb-8">
          <h2 className="text-2xl font-semibold">
            8. Key Performance Indicator
          </h2>
          <p className="mt-2">Define the key performance indicators here.</p>
        </section>
      </main>

      <footer className="w-full h-16 border-t border-gray-300 flex items-center justify-center">
        <p>&copy; 2024 Your Company</p>
      </footer>
    </div>
  );
}
