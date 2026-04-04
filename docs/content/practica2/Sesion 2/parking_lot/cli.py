from datetime import datetime, timedelta
from models.vehicle import Car, Motorcycle
from models.spot import ParkingSpot, SpotType
from models.rates import HourlyRatePolicy
from models.parking_lot import ParkingLot

def main():
    # Configuración de spots específicos 
    spots = [
        ParkingSpot("A1", SpotType.CAR),
        ParkingSpot("M1", SpotType.MOTORCYCLE)
    ]
    policy = HourlyRatePolicy(car_rate=40.0, moto_rate=20.0) # Cobro diferenciado [cite: 109]
    parking = ParkingLot(spots, policy)
    now = datetime.now()

    while True:
        print("\n--- Simulador de Estacionamiento (Sesión 2: Polimorfismo) ---")
        print("1. Registrar entrada")
        print("2. Registrar salida")
        print("3. Ver ocupación")
        print("4. Salir")
        
        opcion = input("Seleccione: ")

        try:
            if opcion == "1":
                placas = input("Placas: ")
                tipo = input("Tipo (C)ar / (M)otorcycle: ").upper()
                
                # Uso de subtipos funcionales [cite: 255]
                v = Car(placas) if tipo == "C" else Motorcycle(placas)
                
                ticket = parking.enter(v, now)
                print(f"Ticket #{ticket.ticket_id} creado. Spot: {ticket.spot.spot_id}")
                
            elif opcion == "2":
                tid = int(input("ID Ticket: "))
                hrs = float(input("Horas: "))
                costo = parking.exit(tid, now + timedelta(hours=hrs))
                print(f"Salida procesada. Costo total: ${costo}")
                
            elif opcion == "3":
                print(f"Estado: {parking.get_occupancy()}")
            elif opcion == "4":
                break
        except Exception as e:
            # Mensajes claros ante errores (ej. estacionamiento lleno) [cite: 252]
            print(f"\n[ALERTA] {e}")

if __name__ == "__main__":
    main()