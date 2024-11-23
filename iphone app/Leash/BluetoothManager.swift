import Foundation
import CoreBluetooth

class BluetoothManager: NSObject, ObservableObject, CBCentralManagerDelegate, CBPeripheralDelegate {
    private var centralManager: CBCentralManager?
    private var selectedPeripheral: CBPeripheral?
    private var toggleCharacteristic: CBCharacteristic?

    @Published var discoveredDevices: [CBPeripheral] = []
    var deviceNames: [String] {
        discoveredDevices.map { $0.name ?? "Unknown Device" }
    }

    override init() {
        super.init()
        centralManager = CBCentralManager(delegate: self, queue: nil)
    }

    func startScanning() {
        if centralManager?.state == .poweredOn {
            discoveredDevices.removeAll()
            centralManager?.scanForPeripherals(withServices: nil, options: nil)
            print("Scanning for all Bluetooth devices...")
        }
    }

    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        if central.state == .poweredOn {
            print("Bluetooth is powered on and ready.")
            startScanning()
        } else {
            print("Bluetooth is not available.")
        }
    }

    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        if !discoveredDevices.contains(peripheral) {
            discoveredDevices.append(peripheral)
            print("Discovered device: \(peripheral.name ?? "Unknown Device")")
        }
    }

    func connectToDevice(named deviceName: String) {
        if let peripheral = discoveredDevices.first(where: { $0.name == deviceName }) {
            selectedPeripheral = peripheral
            selectedPeripheral?.delegate = self
            centralManager?.stopScan()
            centralManager?.connect(peripheral, options: nil)
            print("Attempting to connect to \(deviceName)...")
        }
    }

    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        print("Connected to \(peripheral.name ?? "Unknown Device")")
        peripheral.discoverServices([CBUUID(string: "19B10000-E8F2-537E-4F6C-D104768A1214")])
    }

    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        if let error = error {
            print("Error discovering services: \(error.localizedDescription)")
            return
        }
        
        if let services = peripheral.services {
            for service in services {
                print("Discovered service: \(service.uuid)")
                if service.uuid == CBUUID(string: "19B10000-E8F2-537E-4F6C-D104768A1214") {
                    peripheral.discoverCharacteristics([CBUUID(string: "19B10001-E8F2-537E-4F6C-D104768A1214")], for: service)
                }
            }
        }
    }

    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        if let error = error {
            print("Error discovering characteristics: \(error.localizedDescription)")
            return
        }
        
        if let characteristics = service.characteristics {
            for characteristic in characteristics {
                print("Discovered characteristic: \(characteristic.uuid)")
                if characteristic.uuid == CBUUID(string: "19B10001-E8F2-537E-4F6C-D104768A1214") {
                    toggleCharacteristic = characteristic
                    print("Found toggle characteristic for LED control!")
                }
            }
        }
    }

    func toggleLED() {
        guard let toggleCharacteristic = toggleCharacteristic else {
            print("Toggle characteristic not found!")
            return
        }

        let command = "toggle"
        if let data = command.data(using: .utf8) {
            selectedPeripheral?.writeValue(data, for: toggleCharacteristic, type: .withResponse)
            print("Sent toggle command.")
        }
    }
}
