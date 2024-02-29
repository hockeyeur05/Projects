package model;

public class Technician extends Person {
    private java.lang.String speciality;

    public Technician() {
        super();
        this.speciality = "??";
    }

    public Technician(java.lang.String speciality) {
        super();
        if(speciality!=null) {
            this.speciality = speciality;
        }
    }

    public java.lang.String getSpeciality() {
        return speciality;
    }


    @java.lang.Override
    public boolean isCompatible(Car c) {
        return c instanceof Truck;
    }

    @java.lang.Override
    public java.lang.String toString() {
        return super.toString() +
                "speciality='" + speciality + '\'' +
                '}';
    }
}
