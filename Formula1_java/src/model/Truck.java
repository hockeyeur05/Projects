package model;

public class Truck extends Car {
    private int tonnage;

    public Truck() {
        super();
        this.tonnage = 0;
    }

    public Truck(int tonnage) {
        super();
        if(tonnage>0) {
            this.tonnage = tonnage;
        }
    }

    public int getTonnage() {
        return tonnage;
    }

    @java.lang.Override
    public java.lang.String toString() {
        return super.toString() +
                "tonnage=" + tonnage +
                '}';
    }

    public static void main(String[] args) {
        Truck t1 = new Truck(10);
        System.out.println(t1.toString());
    }
}
