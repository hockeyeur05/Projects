package model;

public class Formula1 extends Car {
    private java.lang.String sponsor;


    public Formula1() {
        super();
        this.sponsor = "??";
    }

    public Formula1(java.lang.String sponsor) {
        super();
        if (sponsor != null) {
            this.sponsor = sponsor;
        }
    }



    public java.lang.String getSponsor() {
        return sponsor;
    }

    public void setSponsor(java.lang.String sponsor) {
        this.sponsor = sponsor;
    }

    @java.lang.Override
    public java.lang.String toString() {
        return super.toString() +
                "sponsor='" + sponsor + '\'' +
                '}';
    }

    public static void main(String[] args) {
        Formula1 f1 = new Formula1("FTX");
        System.out.println(f1.toString());
    }
}


