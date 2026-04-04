from flask import Flask, render_template, request, redirect, url_for, flash
from datetime import datetime, timedelta

# Importamos nuestro modelo ya creado
from models.vehicle import Car, Motorcycle
from models.spot import ParkingSpot, SpotType
from models.rates import HourlyRatePolicy
from models.parking_lot import ParkingLot

app = Flask(__name__)
app.secret_key = "super_secreto_para_flash_messages"  # Necesario para usar flash()

# Inicializamos el estado global en memoria
spots = [
    ParkingSpot("A1", SpotType.CAR),
    ParkingSpot("A2", SpotType.CAR),
    ParkingSpot("M1", SpotType.MOTORCYCLE),
    ParkingSpot("M2", SpotType.MOTORCYCLE),
    ParkingSpot("MIX1", SpotType.ANY)
]
policy = HourlyRatePolicy(car_rate=40.0, moto_rate=20.0)
parking = ParkingLot(spots, policy)

@app.route("/")
def dashboard():
    """Muestra la ocupación y los tickets activos."""
    ocupacion = parking.get_occupancy()
    tickets = parking.get_active_tickets()
    ingresos = parking._total_revenue
    return render_template("dashboard.html", ocupacion=ocupacion, tickets=tickets, ingresos=ingresos)

@app.route("/entry", methods=["GET", "POST"])
def entry():
    """Maneja el registro de entrada."""
    if request.method == "POST":
        placas = request.form.get("plate")
        tipo = request.form.get("type")
        
        # Instanciamos el subtipo correcto (Polimorfismo/Subtipos)
        v = Car(placas) if tipo == "CAR" else Motorcycle(placas)
        now = datetime.now()
        
        try:
            ticket = parking.enter(v, now)
            flash(f"Entrada exitosa. Ticket #{ticket.ticket_id} asignado al spot {ticket.spot.spot_id}", "success")
            return redirect(url_for('dashboard'))
        except ValueError as e:
            # Capturamos errores de validación del modelo
            flash(str(e), "error")
            return redirect(url_for('entry'))
            
    return render_template("entry.html")

@app.route("/exit", methods=["GET", "POST"])
def exit_vehicle():
    """Maneja el registro de salida."""
    if request.method == "POST":
        ticket_id = request.form.get("ticket_id")
        horas_simuladas = request.form.get("hours")
        
        try:
            ticket_id = int(ticket_id)
            horas = float(horas_simuladas)
            
            now = datetime.now()
            exit_time = now + timedelta(hours=horas) # Simulamos el tiempo
            
            costo = parking.exit(ticket_id, exit_time)
            flash(f"Salida procesada. Costo a cobrar: ${costo:.2f}", "success")
            return redirect(url_for('dashboard'))
        except ValueError as e:
            flash(str(e), "error")
            return redirect(url_for('exit_vehicle'))
            
    return render_template("exit.html")

if __name__ == "__main__":
    app.run(debug=True)