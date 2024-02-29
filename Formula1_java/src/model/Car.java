package model;
// An abstract class is a class that cannot be instantiated

public class Car {
    private static int regNum = 0;

    private java.lang.String brand;
    private Engine engine;

    private Person driver;
    public Car() {
        this.regNum ++;
        this.brand = "??";
        this.engine = new Engine();
        this.driver = null;
    }

    public Car(java.lang.String brand){
        this();
        if(brand != null) {
            this.brand = brand;
        }
    }

    public Car(java.lang.String brand,int power, char fuel) {
        this(brand);;
        this.engine = new Engine(power,fuel);
    }

    public Car(java.lang.String brand, Engine engine) {
        this(brand);
        this.engine = new Engine(engine);
    }

    public static int getRegNum() {
        return regNum;
    }

    public java.lang.String getBrand() {
        return brand;
    }

    public Engine getCopyEngine() {
        return new Engine(engine);
    }

    public Person getCopyDriver() {
        return new Person(this.driver);
    }

    public void setEngine(Engine engine) {
        if(engine != null) {
            this.engine = engine;
        }
    }

    public boolean isAvailable() {
        return this.driver == null;
    }
    public boolean setDriver(Person p) {
        if(p==null) return false;
        if(!this.isAvailable()){
            return false;
        }
        if(!p.isDriving(this)) {
            return false;
        }
        p.car = this;
        return true;
    }

    @java.lang.Override
    public java.lang.String toString() {
        return "Car{" +
                "brand=" + brand +
                ", engine=" + engine +
                ", driver=" + driver +
                '}';
    }

    public static void main(String[] args) {
        //Engine e1 = new Engine(null);
        Engine e2 = new Engine(1000,'E');
       // Car c1 = new Car(null, e1);
        Car c2 = new Car("Ferrari", e2);
        Car c3 = new Car("Ferrari", e2);
       // System.out.println("c1 : " + c1.toString());
        System.out.println("c2 : " + c2.toString());
        System.out.println("c3 : " + c3.toString());
        e2.setPower(1200);
        System.out.println("c2 : " + c2.toString());
        System.out.println("c3 : " + c3.toString());

    }
}