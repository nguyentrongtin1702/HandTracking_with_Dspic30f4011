from cvzone.HandTrackingModule import HandDetector
import cv2
import serial

ser = serial.Serial("COM3", 9600, bytesize=8, parity='N', stopbits=1, timeout=1)

# Initialize the webcam to capture video
if ser.isOpen():
    cap = cv2.VideoCapture(0)

    # Initialize the HandDetector class
    detector = HandDetector(staticMode=False, maxHands=2, modelComplexity=1, detectionCon=0.5, minTrackCon=0.5)

    while True:
        # Capture each frame from the webcam
        success, img = cap.read()

        # Detect hands in the current frame
        hands, img = detector.findHands(img, draw=True, flipType=True)

        if hands:
            # Information for the first hand detected
            hand1 = hands[0]
            lmList1 = hand1["lmList"]
            fingers1 = detector.fingersUp(hand1)
            num_fingers1 = fingers1.count(1)

            # Send the number of fingers up to the microcontroller as a single byte
            ser.write(str(num_fingers1).encode('utf-8'))
            print(f'H1 = {num_fingers1}', end=" ")

            # Calculate distance between landmarks on the first hand
           #length, info, img = detector.findDistance(lmList1[8][0:2], lmList1[12][0:2], img, color=(255, 0, 255),
                                                      #scale=10)

            #if len(hands) == 2:
                # Information for the second hand
                #hand2 = hands[1]
                #lmList2 = hand2["lmList"]
                #fingers2 = detector.fingersUp(hand2)
                #num_fingers2 = fingers2.count(1)

                # Send the number of fingers up for the second hand
                #ser.write(bytes([num_fingers2]))
                #print(f'H2 = {num_fingers2}', end=" ")

                # Calculate distance between the index fingers of both hands
                #length, info, img = detector.findDistance(lmList1[8][0:2], lmList2[8][0:2], img, color=(255, 0, 0),
                                                          #scale=10)

            print(" ")  # New line for better readability

        # Display the image in a window
        cv2.imshow("Image", img)
        cv2.waitKey(1)
