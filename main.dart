import 'package:flutter/material.dart';
import 'services/api_service.dart';
import 'dart:async'; // Tambahkan import ini

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter API Example',
      home: HomeScreen(),
    );
  }
}

class HomeScreen extends StatefulWidget {
  @override
  _HomeScreenState createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  Map<String, dynamic>? sensorData;
  Timer? _timer; // Timer untuk auto-reload

  @override
  void initState() {
    super.initState();
    _fetchData();

    // Set Timer untuk auto-reload data setiap 5 detik
    _timer = Timer.periodic(Duration(seconds: 1), (Timer t) => _fetchData());
  }

  @override
  void dispose() {
    _timer?.cancel(); // Pastikan timer berhenti saat screen ditutup
    super.dispose();
  }

  void _fetchData() async {
    sensorData = await ApiService.fetchSensorData();
    setState(() {});
  }

  @override
Widget build(BuildContext context) {
  return Scaffold(
    appBar: AppBar(
      title: Text('Sensor Data'),
    ),
    body: sensorData == null
        ? Center(child: CircularProgressIndicator())
        : Padding(
            padding: const EdgeInsets.all(16.0),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text("Level: ${sensorData!['sensor_data']['sensor_data_6']['level']}"),
                Text("Voltage: ${sensorData!['sensor_data']['sensor_data_6']['voltage']} V"),
                Text("Current: ${sensorData!['sensor_data']['sensor_data_6']['current']} A"),
                Text("Temperature: ${sensorData!['sensor_data']['sensor_data_6']['temp']} °C"),
                Text("Charging: ${sensorData!['sensor_data']['sensor_data_6']['charging'] ? 'Yes' : 'No'}"),
                Text("Cooler: ${sensorData!['sensor_data']['sensor_data_6']['cooler'] ? 'Yes' : 'No'}"),
                Text("Heater: ${sensorData!['sensor_data']['sensor_data_6']['heater'] ? 'Yes' : 'No'}"),
              ],
            ),
          ),
  );
}
}
