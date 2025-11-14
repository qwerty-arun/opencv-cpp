# 🔹 Practice Program List (Step-by-Step Learning Path)

## 🟢 Beginner (Basics of OpenCV)

- [x] Load, display, and save an image.
- [x] Convert to grayscale.
- [x] Resize and rotate an image.
- [x] Crop a region of interest (ROI).
- [x] Draw lines, circles, rectangles, and text on an image.
- [x] Blend two images (addWeighted).
- [x] Apply Gaussian blur, median blur.
- [x] Edge detection (Canny).
- [x] Print individual pixel values.
- [x] Split color image to BGR.
- [x] Flip images.

## 🟡 Intermediate (Image Processing)

- [x] Histogram calculation for grayscale images.
- [x] Histogram calculation for color images.
- [x] Equalisation calculation.
- [x] Thresholding (simple, adaptive, Otsu).
- [x] Morphological operations (erosion, dilation, opening, closing).
- [x] Detect and draw contours.
- [ ] Image pyramids (pyrUp, pyrDown).
- [ ] Perspective transform (warp image).
- [ ] Color detection using HSV (detect red, green, blue objects).

## 🔵 Advanced (Computer Vision & Fun Projects)

- [ ] Face detection using Haar cascades.
- [ ] Eye detection.
- [ ] Real-time object tracking with color.
- [ ] Motion detection using frame differencing.
- [ ] Background subtraction (MOG2).
- [ ] Barcode/QR code detection.
- [ ] Simple Augmented Reality (overlay an image on detected marker).

# Projects

## **Beginner Projects (Build Core OpenCV Skills)**

### **1. Image Filters & Transformations**

- Gaussian blur, sharpening, edge detection (Canny, Sobel)
- Rotate/scale/crop
- Convert RGB ↔ HSV ↔ Gray
  **Skills:** Mat operations, basic image pipeline
  **Add-ons:** Implement your own convolution kernel.

### **2. Real-time Webcam Effects**

- Cartoon effect
- Pencil sketch effect
- Background color swapping
  **Skills:** VideoCapture, frame-by-frame pipeline.

### **3. Color Detection & Object Tracking**

- Track red objects using HSV thresholding
- Draw bounding boxes / contours
  **Skills:** Thresholding, morphology, contour detection.

---

## **Intermediate Projects (Useful + Resume Worthy)**

### **4. Motion Detection & Object Counting**

- Use frame-differencing or MOG2 background subtractor
- Count vehicles/people passing ROI
  **Skills:** Background subtraction, contours, filtering noise.

### **5. Face & Eye Detection (Haar / DNN)**

- Viola–Jones classifiers
- Or DNN-based SSD models
  **Skills:** Feature detection + DNN inference.

### **6. Lane Detection for Self-Driving Cars**

- Canny edges → Hough lines
- Perspective transform
  **Skills:** Image processing + geometry
  **Add-on:** PID to keep virtual car in lane.

### **7. Basic OCR Pipeline (without Tesseract)**

- Extract characters using contour segmentation
- Recognize digits using k-NN / SVM
  **Skills:** Preprocessing, machine learning basics.

### **8. Shape Detection**

- Identify triangles, rectangles, circles in real time
  **Skills:** Contours, approxPolyDP, Hough Circles.

---

## **Advanced Projects (Robotics, ADAS, Computer Vision)**

### **9. Real-Time Object Detector (YOLO + OpenCV DNN)**

- Use pretrained YOLOv3/v4
- Build a clean C++ inference pipeline
  **Skills:** DNN, threading, GPU acceleration.

### **10. Gesture Recognition Using Hand Tracking**

- Skin segmentation or MediaPipe hand landmarks
- Recognize “swipe”, “zoom”, “grab” gestures
  **Skills:** Tracking + temporal analysis.

### **11. Vehicle Detection & Speed Estimation**

- Detect cars using HOG + SVM / YOLO
- Track with Kalman filter
- Estimate speed using pixel → real-world mapping
  **Skills:** Tracking, filtering, calibration.

### **12. SLAM (Semi-Minimal Version)**

- Feature extraction (ORB/SIFT)
- Feature matching (FLANN/BruteForce)
- Estimate camera motion using Essential Matrix
  **Skills:** Epipolar geometry + robotics CV.

### **13. Augmented Reality Marker Tracking**

- Detect ArUco markers
- Estimate camera pose
- Overlay 3D cube on them
  **Skills:** pose estimation, camera calibration.

### **14. License Plate Detection & Character Segmentation**

- Edge-based plate extraction
- Morphology for isolation
- Segment individual characters
  **Skills:** end-to-end pipeline + useful application.

---

# 🚀 **Expert-Level / Research-Style Projects**

### **15. Multi-Object Tracking (DeepSORT-style)**

- Combine YOLO → Kalman → Hungarian algorithm
  **Skills:** Real-world tracking pipeline.

### **16. Stereo Vision Depth Map**

- Calibrate two cameras
- Build disparity map
- Real-world depth estimation
  **Skills:** 3D reconstruction.

### **17. Optical Flow-based Pedestrian Tracking**

- Lucas-Kanade / Farneback
- Reidentify moving objects
  **Skills:** motion vectors + tracking.

### **18. Image Stitching (Panorama)**

- Use SIFT/ORB for matching
- RANSAC for homography
- Warp + blend images
  **Skills:** projective transforms, blending.

---
