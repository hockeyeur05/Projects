package model;

public class Driver extends Person {
    private int nbPrizes;
    private int nbWithdrawals;

    public Driver() {
        super();
        this.nbPrizes = 0;
        this.nbWithdrawals = 0;
    }

    public Driver(java.lang.String surname, java.lang.String name, java.lang.String address) {
        super(surname,name,address,null);
    }
    public Driver(java.lang.String surname, java.lang.String name, java.lang.String address, Car car,int nbPrizes,int nbWithdrawals) {
        super(surname,name,address,car);
        this.nbWithdrawals = nbWithdrawals;
        this.nbPrizes = nbPrizes;
    }

    public int getNbPrizes() {
        return nbPrizes;
    }

    public int getNbWithdrawals() {
        return nbWithdrawals;
    }

    public void setNbPrizes(int nbPrizes) {
        if(nbPrizes>=0) {
            if(nbPrizes>this.nbPrizes) {
                if((nbPrizes-this.nbPrizes)==1) {
                    this.nbPrizes = nbPrizes;
                }
            }
            else {
                this.nbPrizes = nbPrizes;
            }
        }
        this.nbPrizes = nbPrizes;
    }

    public void setNbWithdrawals(int nbWithdrawals) {
        if(nbWithdrawals > this.nbWithdrawals) {
            this.nbWithdrawals = nbWithdrawals;
        }
    }

    @java.lang.Override
    public boolean isCompatible(Car c) {
        return c instanceof Formula1;
    }

    @java.lang.Override
    public java.lang.String toString() {

        return super.toString() +
                "nbPrizes=" + nbPrizes +
                ", nbWithdrawals=" + nbWithdrawals +
                '}';
    }


    public static void main(String[] args) {
        Engine e1 = new Engine(700,'D');
        Engine e2 = new Engine(1000,'E');
        Car c1 = new Car("Ferrari", e1);
        Car c2 = new Car("Ferrari", e2);
        Driver d1 = new Driver("lj","jyf","tgfd",c1,0,2);
        Person d2 = new Driver("aa","bb","cc",c2,7,3);
        System.out.println(d1.toString());
        System.out.println(d2.toString());
    }
}