package org.ioopm.calculator;

public class Stats {
    public int expressions;
    public int fulleval;
    public int successeval;

    public Stats() {
        this.expressions = 0;
        this.fulleval = 0;
        this.successeval = 0;
    }

    public void addExpression() {
        this.expressions += 1;
    }

    public void addFullEval() {
        this.fulleval += 1;
        this.successeval += 1;
    }

    public void addSuccEval() {
        this.successeval += 1;
    }
    
    public void printstats()
    {
        System.out.println("Expressions entered:" + this.expressions);
        System.out.println("Fully evaluated:" + this.fulleval);
        System.out.println("Successfully evaluated:" + this.successeval);
    }
}
