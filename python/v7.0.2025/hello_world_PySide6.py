import sys
from PySide6 import QtCore, QtWidgets

# Create a Qt application
app = QtWidgets.QApplication(sys.argv)

# Create a Qt window
main_window = QtWidgets.QWidget()
main_window.resize(320, 240)
main_window.setWindowTitle("'Hello, world!' example")

# Create text in the window
label = QtWidgets.QLabel(main_window)
label.setText("Hello, world!")
label.setGeometry(QtCore.QRect(10, 10, 300, 220))
label.setStyleSheet("background-color: lightblue; padding: 10px;")  # Set background color to light blue

# Show the window
main_window.show()

# Enter the Qt main loop and exit when done
sys.exit(app.exec())
