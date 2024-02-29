package model;
public abstract class Person {
    private static int id = 0;
    private java.lang.String surname;

    private java.lang.String name;

    private java.lang.String address;

    private Car car;

    private boolean isPedestrian = true;

    public boolean isPedestrian() {
        return (this.car == null);
    }
    public Person() {
        this.id++;
        this.name = "";
        this.surname = "";
        this.address = "";
        this.car = null;
        this.isPedestrian = true;
    }

    public Person(Person otherPerson) {
        this.name = otherPerson.name;
        this.surname = otherPerson.surname;
        this.address = otherPerson.address;
        this.car = otherPerson.car;
        this.isPedestrian = otherPerson.isPedestrian;

    }

    public Person(java.lang.String surname, java.lang.String name, java.lang.String address, Car car) {
        this();
        if(surname != null) {
            this.surname = surname;
        }
        if(name != null) {
            this.name = name;
        }
        if(address != null) {
            this.address = address;
        }
        this.car = car;
        this.isPedestrian = isPedestrian();
    }

    public int getId() {
        return id;
    }

    public java.lang.String getName() {
        return name;
    }

    public java.lang.String getSurname() {
        return surname;
    }

    public java.lang.String getAddress() {
        return address;
    }

    public Car getCar() {
        return car;
    }

    public void setAddress(java.lang.String address) {
        if(address != null) {
            this.address = address;
        }
    }
/*
    public boolean assign(Car c) {
        if(car != null) {
            if(this.isPedestrian) {
                this.car = car;
                this.car.setDriver(this);
            }
        }
        return (this.car == c);
    }

    public boolean isDriving(Car c) { //à refaire
        if(!c.isAvailable()) {
            return false;
        return true;
    }

    public boolean returnCar() {
        if(this.isPedestrian) {
            return false;
        }

        else {
            if(this.car != null) {
                System.out.println(this.car.toString());
            }
        }
        return true;
    }*/

    public abstract boolean isCompatible(Car c);
    @java.lang.Override
    public java.lang.String toString() {
        return "Person{" +
                "surname='" + surname + '\'' +
                ", name='" + name + '\'' +
                ", address='" + address + '\'' +
                ", car=" + car +
                ", isPedestrian=" + isPedestrian +
                '}';
    }

    public static void main(String[] args) {
        Engine e1 = new Engine(700,'D');
        Engine e2 = new Engine(1000,'E');
        Car c1 = new Car("Ferrari", e1);
        Car c2 = new Car("Ferrari", e2);
        Person p1 = new Person("lj","jyf","tgfd",c1);
        Person p2 = new Person("aa","bb","cc",c2);
        //p1.assign(c2);
        System.out.println(p1.toString());
        System.out.println(p2.toString());
    }
}