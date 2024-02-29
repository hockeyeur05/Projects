package model;

public class Engine {
    //attributes
    /**
     * power expressed in hp
     * should be grater than 600
     */

    private int power;
    /**
     * fuel can be either diesel (D) or petrol (P)
     */
    private char fuel;
    //constants = static + final (final means that you can't change it in the future)
    //written in capital letters, word separated with '_'
    private static final int MIN_POWER = 600;
    private static final char DIESEL = 'D';
    private static final char PETROL = 'P';

    //constructors

    /**
     * default constructors : minimum power and petrol
     */
    public Engine() {
        //this refers to the current instance of the class (here the one we are building)
        this.power = MIN_POWER;
        this.fuel = PETROL;
    }

    /**
     * data constructor
     * @param power power in hp (should be greater than MIN_POWER
     * @param fuel fuel should be either petrol (P) or diesel (D)
     */
    public Engine(int power, char fuel) {
        this(); // this() = call to the default constructor
                // it can be written only as first statement of a constructor
                // inside the parenthesis you can call another data constructor
        if(power>MIN_POWER) {
            this.power = power;
        }
        if(fuel == DIESEL) {
            this.fuel = fuel;
        }
    }

    /**
     * copy constructor
     * @param anotherEngine the engine to be copied
     */
    public Engine(Engine anotherEngine) {
        this();
        if(anotherEngine != null) {
            this.power = anotherEngine.power;
            this.fuel = anotherEngine.fuel;
        }
    }

    // methods


    public int getPower() {
        return power; //equivalent to this.power
    }

    public char getFuel() {
        return fuel; //equivalent to this.fuel
    }

    /**
     * modify the power of an engine
     * modification only performed if we provide a correct value
     * @param power new power
     */
    public void setPower(int power) {
        if(power >= MIN_POWER) {
            this.power = power;
        }
    }

    @java.lang.Override
    public java.lang.String toString() {
        return "Engine{" +
                "power=" + power +
                ", fuel=" + fuel +
                '}';
    }

    public static void main(String[] args) {
        Engine e1 = new Engine(); // new to call a constructor : here we are calling the default one
        Engine e2 = new Engine(1200,'P');
        Engine e3 = new Engine(1400,'D');
        Engine e4 = new Engine(700,'a');
        Engine e5 = new Engine(100,'D');
        Engine e6 = new Engine(e1); // call to copy constructor
        e1.setPower(1000);
        e2.setPower(120);
        System.out.println(e1.toString());
        /* it will call implicitly the string method */
        System.out.println(e2);
        System.out.println(e3);
        System.out.println(e4);
        System.out.println(e5);
        System.out.println(e6); /* e6 is not modified by the modification of e1 because the modification
                                is done after the copy*/

    }
}
