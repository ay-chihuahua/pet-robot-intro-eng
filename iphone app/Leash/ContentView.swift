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

            // Button to toggle the LED
            Button(action: {
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
        }
    }
}
