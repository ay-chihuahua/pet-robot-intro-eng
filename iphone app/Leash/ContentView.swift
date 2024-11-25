import SwiftUI

struct ContentView: View {
    @StateObject private var bluetoothManager = BluetoothManager()

    var body: some View {
        VStack {
            Text("Discovered Devices")
                .font(.headline)
                .padding()

            // Display list of device names
            List(bluetoothManager.deviceNames, id: \.self) { deviceName in
                Button(action: {
                    bluetoothManager.connectToDevice(named: deviceName) // Connect on tap
                }) {
                    Text(deviceName)
                }
            }
            .frame(maxHeight: 300)

            // Button to start scanning
            Button(action: {
                bluetoothManager.startScanning()
            }) {
                Text("Scan for Devices")
                    .font(.title2)
                    .padding()
                    .background(Color.blue)
                    .foregroundColor(.white)
                    .cornerRadius(10)
            }
            .padding()

            Button(action: { // Button to toggle the LED
                bluetoothManager.toggleLED()
            }) {
                Text("Toggle LED")
                    .font(.title2)
                    .padding()
                    .background(Color.green)
                    .foregroundColor(.white)
                    .cornerRadius(10)
            }
            .padding()
           
            Button(action: { // Button to walk forward
                bluetoothManager.walkForward()
            }) {
                Text("Walk Forward")
                    .font(.title2)
                    .padding()
                    .background(Color.green)
                    .foregroundColor(.white)
                    .cornerRadius(10)
            }
            .padding()
            
            Button(action: { // Button to walk backwards
                bluetoothManager.walkBackwards()
            }) {
                Text("Walk Backwards")
                    .font(.title2)
                    .padding()
                    .background(Color.green)
                    .foregroundColor(.white)
                    .cornerRadius(10)
            }
            .padding()
            
            Button(action: { // Button to lay down
                bluetoothManager.layDown()
            }) {
                Text("Lay down")
                    .font(.title2)
                    .padding()
                    .background(Color.green)
                    .foregroundColor(.white)
                    .cornerRadius(10)
            }
            .padding()
            
            Button(action: { // Button to bark
                bluetoothManager.bark()
            }) {
                Text("Speak")
                    .font(.title2)
                    .padding()
                    .background(Color.green)
                    .foregroundColor(.white)
                    .cornerRadius(10)
            }
            .padding()
            
        }
    }
}
