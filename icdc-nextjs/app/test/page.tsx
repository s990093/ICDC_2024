"use client";
import React, { useRef } from "react";
import { Canvas, useFrame } from "@react-three/fiber";
import { Mesh } from "three";

const MovingBox: React.FC = () => {
  const meshRef = useRef<Mesh>(null);
  const speed = 0.1; // 移動速度

  useFrame(() => {
    if (meshRef.current) {
      meshRef.current.position.x += speed;
      if (meshRef.current.position.x > 5) {
        meshRef.current.position.x = -5; // 如果超出範圍，重置位置
      }
    }
  });

  return (
    <mesh ref={meshRef}>
      <boxGeometry args={[2, 2, 2]} />
      <meshStandardMaterial color="orange" />
    </mesh>
  );
};

const App: React.FC = () => {
  return (
    <Canvas>
      <ambientLight intensity={0.5} />
      <pointLight position={[10, 10, 10]} />
      <MovingBox />
    </Canvas>
  );
};

export default App;
