using System;

namespace TransportSystem
{
    //1.
    public interface IVehicle
    {
        void Drive();
        void Refuel();
    }

    //2.
    public class Car : IVehicle
    {
        private string _brand, _model, _fuelType;
        public Car(string brand, string model, string fuelType) 
        { 
            _brand = brand; _model = model; _fuelType = fuelType; 
        }
        public void Drive() => Console.WriteLine($"Едем на автомобиле {_brand} {_model}.");
        public void Refuel() => Console.WriteLine($"Заправка автомобиля типом топлива: {_fuelType}.");
    }

    public class Motorcycle : IVehicle
    {
        private string _type;
        private int _engineVolume;
        public Motorcycle(string type, int engineVolume) 
        { 
            _type = type; _engineVolume = engineVolume; 
        }
        public void Drive() => Console.WriteLine($"Мчимся на {_type} мотоцикле ({_engineVolume} см³).");
        public void Refuel() => Console.WriteLine("Заправка мотоцикла бензином.");
    }

    public class Truck : IVehicle
    {
        private double _capacity;
        private int _axles;
        public Truck(double capacity, int axles) 
        { 
            _capacity = capacity; _axles = axles; 
        }
        public void Drive() => Console.WriteLine($"Перевозка груза на {_axles}-осном грузовике ({_capacity} тонн).");
        public void Refuel() => Console.WriteLine("Заправка грузовика дизелем.");
    }

    public class Bus : IVehicle
    {
        private int _seatingCapacity;
        public Bus(int seatingCapacity) { _seatingCapacity = seatingCapacity; }
        public void Drive() => Console.WriteLine($"Перевозка {_seatingCapacity} пассажиров на автобусе.");
        public void Refuel() => Console.WriteLine("Заправка автобуса газом.");
    }

    //3)
    public abstract class VehicleFactory
    {
        public abstract IVehicle CreateVehicle();
    }

    //4.
    public class CarFactory : VehicleFactory
    {
        private string _b, _m, _f;
        public CarFactory(string b, string m, string f) { _b = b; _m = m; _f = f; }
        public override IVehicle CreateVehicle() => new Car(_b, _m, _f);
    }

    public class MotorcycleFactory : VehicleFactory
    {
        private string _t;
        private int _v;
        public MotorcycleFactory(string t, int v) { _t = t; _v = v; }
        public override IVehicle CreateVehicle() => new Motorcycle(_t, _v);
    }

    public class TruckFactory : VehicleFactory
    {
        private double _c;
        private int _a;
        public TruckFactory(double c, int a) { _c = c; _a = a; }
        public override IVehicle CreateVehicle() => new Truck(_c, _a);
    }

    public class BusFactory : VehicleFactory
    {
        private int _s;
        public BusFactory(int s) { _s = s; }
        public override IVehicle CreateVehicle() => new Bus(_s);
    }

    //5)
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Выберите тип транспорта: 1-Автомобиль, 2-Мотоцикл, 3-Грузовик, 4-Автобус");
            string choice = Console.ReadLine();
            VehicleFactory factory = null;

            try
            {
                switch (choice)
                {
                    case "1":
                        Console.Write("Введите марку: "); string brand = Console.ReadLine();
                        Console.Write("Введите модель: "); string model = Console.ReadLine();
                        Console.Write("Введите тип топлива: "); string fuel = Console.ReadLine();
                        factory = new CarFactory(brand, model, fuel);
                        break;
                    case "2":
                        Console.Write("Введите тип (Sport/Touring): "); string type = Console.ReadLine();
                        Console.Write("Введите объем двигателя: "); int vol = int.Parse(Console.ReadLine());
                        factory = new MotorcycleFactory(type, vol);
                        break;
                    case "3":
                        Console.Write("Введите грузоподъемность (тонн): "); double cap = double.Parse(Console.ReadLine());
                        Console.Write("Введите количество осей: "); int axles = int.Parse(Console.ReadLine());
                        factory = new TruckFactory(cap, axles);
                        break;
                    case "4":
                        Console.Write("Введите количество мест: "); int seats = int.Parse(Console.ReadLine());
                        factory = new BusFactory(seats);
                        break;
                    default:
                        Console.WriteLine("Ошибка: Неверный выбор.");
                        return;
                }

                // Создание и использование объекта через фабрику
                IVehicle vehicle = factory.CreateVehicle();
                Console.WriteLine("\n--- Работа транспорта ---");
                vehicle.Drive();
                vehicle.Refuel();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка ввода: {ex.Message}");
            }

            Console.WriteLine("\nНажмите любую клавишу для выхода...");
            Console.ReadKey();
        }
    }
}