package model;

public class Team {
    private java.lang.String name;

    private static final int MAXLEN = 5;

    private Person[] staff;

    private Car[] fleet;

    public boolean isMember(Person p) {
        int n = this.staff.length;
        for(int i=0;i<n;i++) {
            if (this.staff[i] == p) {
                return true;
            }
        }
        return false;
    }

    public boolean isInFleet(Car c) {
        int n = this.fleet.length;
        for(int i=0;i<n;i++) {
            if (this.fleet[i] == c) {
                return true;
            }
        }
        return false;
    }

    public void hire(Person p) {
        int n = this.staff.length;
        Person[] new_staff = new Person[n+1];
        for(int i=0;i<n;i++) {
            new_staff[i] = this.staff[i];
        }
        new_staff[n] = p;
        this.staff = new_staff;
    }


}
