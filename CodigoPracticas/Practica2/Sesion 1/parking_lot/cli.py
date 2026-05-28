from datetime import datetime, timedelta
from models.vehicle import Vehicle, VehicleType
from models.spot import ParkingSpot, SpotType
from models.rates import HourlyRatePolicy
from models.parking_lot import ParkingLot

def main():
    # Inicialización de datos en memoria
    spots = [
        ParkingSpot("A1", SpotType.CAR),
        ParkingSpot("A2", SpotType.CAR),
        ParkingSpot("M1", SpotType.MOTORCYCLE),
        ParkingSpot("M2", SpotType.MOTORCYCLE),
    ]
    policy = HourlyRatePolicy(car_rate=20.0, moto_rate=10.0)
    parking = ParkingLot(spots, policy)
    
    # Hora base para la simulación
    now = datetime.now()

    while True:
        print("\n--- Simulador de Estacionamiento ---")
        print("1. Registrar entrada")
        print("2. Registrar salida")
        print("3. Ver ocupación")
        print("4. Ver tickets activos")
        print("5. Salir")
        
        opcion = input("Elige una opción: ")

        try:
            if opcion == "1":
                placas = input("Placas: ")
                tipo_str = input("Tipo (CAR/MOTORCYCLE): ").upper()
                tipo = VehicleType[tipo_str]
                v = Vehicle(placas, tipo)
                
                ticket = parking.enter(v, now)
                print(f"Entrada exitosa -> Ticket #{ticket.ticket_id}, spot={ticket.spot.spot_id}")
                
            elif opcion == "2":
                ticket_id = int(input("ID del ticket: "))
                # Simulamos las horas pasadas sumándolas al 'now' inicial
                horas_simuladas = float(input("Horas transcurridas (simulación): "))
                salida_time = now + timedelta(hours=horas_simuladas)
                
                # Obtenemos el spot antes de procesar la salida para mostrarlo
                ticket_obj = parking._active_tickets.get(ticket_id) 
                spot_id = ticket_obj.spot.spot_id if ticket_obj else "Desconocido"

                costo = parking.exit(ticket_id, salida_time)
                print(f"Salida: ticket={ticket_id} -> tiempo={horas_simuladas}h costo ${costo:.2f} spot liberado={spot_id}")
                
            elif opcion == "3":
                print(f"Ocupación: {parking.get_occupancy()}")
                
            elif opcion == "4":
                tickets = parking.get_active_tickets()
                activos = [f"#{t.ticket_id}" for t in tickets]
                print(f"Tickets activos: [{', '.join(activos)}]")
                
            elif opcion == "5":
                print("Cerrando sistema...")
                break
            else:
                print("Opción inválida. Intenta de nuevo.")
        except Exception as e:
            print(f"Error: {e}")

if __name__ == "__main__":
    main()