package org.ioopm.calculator.parser;

import org.ioopm.calculator.ast.*;

import java.io.StreamTokenizer;
import java.io.StringReader;
import java.io.IOException;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.function.Function;

import javax.management.RuntimeErrorException;

/**
 * Represents the parsing of strings into valid expressions defined in the AST.
 */
public class CalculatorParser {
    private StreamTokenizer st;
    private Environment vars;
    private static char MULTIPLY = '*';
    private static char ADDITION = '+';
    private static char SUBTRACTION = '-';
    private static char DIVISION = '/';
    private static String NEG = "Neg";
    private static char NEGATION = '-';
    private static String SIN = "Sin";
    private static String COS = "Cos";
    private static String LOG = "Log";
    private static String EXP = "Exp";
    private static char ASSIGNMENT = '=';
    private static char OPEN_SCOPE = '{';
    private static char CLOSE_SCOPE = '}';
    private static String IF  = "if";
    private static String ELSE = "else";
    private static char GT = '>';
    private static char LT = '<';
    private static String GTE = ">=";
    private static String LTE = "<=";
    private static String EQUALS = "==";
    private static String FUNCTION = "function";


    private boolean functionParsingMode = false;

    public boolean getFunctionParsingMode() {
        return functionParsingMode;
    }


    // unallowerdVars is used to check if variabel name that we
    // want to assign new meaning to is a valid name eg 3 = Quit
    // or 10 + x = L is not allowed
    private final ArrayList < String > unallowedVars = new ArrayList < String > (Arrays.asList("Quit",
        "Vars",
        "Clear"));

    /**
     * Used to parse the inputted string by the Calculator program
     * @param inputString the string used to parse
     * @param vars the Environment in which the variables exist
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    public SymbolicExpression parse(String inputString, Environment vars) throws IOException {

        // StringTokenizer setup
        this.st = new StreamTokenizer(new StringReader(inputString)); // reads from inputString via stringreader.  
        this.st.ordinaryChar('-');
        this.st.ordinaryChar('/');
        this.st.eolIsSignificant(true);

        this.vars = vars;
        SymbolicExpression result = statement(); // calls to statement
        return result; // the final result
    }

    /**
     * Checks wether the token read is a command or an assignment
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression
     */
    private SymbolicExpression statement() throws IOException {
        SymbolicExpression result;
        this.st.nextToken(); //kollar pÃ¥ nÃ¤sta token som ligger pÃ¥ strÃ¶mmen
        if (this.st.ttype == StreamTokenizer.TT_EOF) {
            throw new SyntaxErrorException("Error: Expected an expression");
        }

        if (this.st.ttype == StreamTokenizer.TT_WORD) { // vilken typ det senaste tecken vi lÃ¤ste in hade.
            if (this.st.sval.equals("Quit") || this.st.sval.equals("Vars") || this.st.sval.equals("Clear")) { // sval = string Variable
                result = command();
            } else {
                result = assignment(); // går vidare med uttrycket.
            }
        } else {
            result = assignment(); // om inte == word, gå till assignment ändå (kan vara tt_number)
        }

        if (this.st.nextToken() != StreamTokenizer.TT_EOF) { // token should be an end of stream token if we are done
            if (this.st.ttype == StreamTokenizer.TT_WORD) {
                throw new SyntaxErrorException("Error: Unexpected '" + this.st.sval + "'");
            } else {
                throw new SyntaxErrorException("Error: Unexpected '" + String.valueOf((char) this.st.ttype) + "'");
            }
        }
        return result;
    }


    /**
     * Checks what kind of command that should be returned
     * @return an instance of Quit, Clear or Vars depending on the token parsed
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression command() throws IOException {
        if (this.st.sval.equals("Quit")) {
            return Quit.instance();
        } else if (this.st.sval.equals("Clear")) {
            return Clear.instance();
        } else if (this.st.sval.equals("Vars")) {
            return Vars.instance();
        } else {
            if(functionParsingMode) {
                functionParsingMode = false;
                return End.instance();
            } else {
                throw new RuntimeException("End can only occur as end of function definition");
            }
            
        }  
    }


    /**
     * Checks wether the token read is an assignment between 2 expression and 
     * descend into the right hand side of '='
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression,
     *         the variable on rhs of '=' is a number or invalid variable
     */
    private SymbolicExpression assignment() throws IOException {
        SymbolicExpression result = expression();
        this.st.nextToken();
        while (this.st.ttype == ASSIGNMENT) {
            this.st.nextToken();
            if (this.st.ttype == StreamTokenizer.TT_NUMBER) {
                throw new SyntaxErrorException("Error: Numbers cannot be used as a variable name");
            } else if (this.st.ttype != StreamTokenizer.TT_WORD) {
                throw new SyntaxErrorException("Error: Not a valid assignment of a variable"); //this handles faulty inputs after the equal sign eg. 1 = (x etc
            } else {
                if (this.st.sval.equals("ans")) {
                    throw new SyntaxErrorException("Error: ans cannot be redefined");
                }
                SymbolicExpression key = identifier();
                result = new Assignment(result, key);
            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Check if valid identifier for variable and return that if so
     * @return a SymbolicExpression that is either a named constant or a new variable
     * @throws IOException by nextToken() if it reads invalid input
     * @throws IllegalExpressionException if you try to redefine a string that isn't allowed
     */
    private SymbolicExpression identifier() throws IOException {
        SymbolicExpression result;

        if (this.unallowedVars.contains(this.st.sval)) {
            throw new IllegalExpressionException("Error: cannot redefine " + this.st.sval);
        }

        if (Constants.namedConstants.containsKey(this.st.sval)) {
            result = new NamedConstant(st.sval, Constants.namedConstants.get(st.sval));
            vars.put(new Variable(this.st.sval), new Constant(Constants.namedConstants.get(this.st.sval)));
        } else {
            result = new Variable(this.st.sval);
        }
        return result;
    }


    /**
     * Checks wether the token read is an addition or subtraction
     * and then continue on with the right hand side of operator
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression expression() throws IOException {
        SymbolicExpression result = term();
        this.st.nextToken();
        while (this.st.ttype == ADDITION || this.st.ttype == SUBTRACTION) {
            int operation = st.ttype;
            this.st.nextToken();
            if (operation == ADDITION) {
                result = new Addition(result, term());
            } else {
                result = new Subtraction(result, term());
            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Checks wether the token read is an Multiplication or
     * Division and then continue on with the right hand side of
     * operator
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression term() throws IOException {
        SymbolicExpression result = primary();
        this.st.nextToken();
        while (this.st.ttype == MULTIPLY || this.st.ttype == DIVISION) {
            int operation = st.ttype;
            this.st.nextToken();

            if (operation == MULTIPLY) {
                result = new Multiplication(result, primary());
            } else {
                result = new Division(result, primary());
            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Checks wether the token read is a parantheses and then
     * continue on with the expression inside of it or if the
     * operation is an unary operation and then continue on with
     * the right hand side of that operator else if it's a
     * number/identifier
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression,
     *         missing right parantheses
     */
    private SymbolicExpression primary() throws IOException {
        SymbolicExpression result;
        if (this.st.ttype == '(') {
            this.st.nextToken();
            result = assignment();
            /// This captures unbalanced parentheses!
            if (this.st.nextToken() != ')') {
                throw new SyntaxErrorException("expected ')'");
            }
        } else if (this.st.ttype == NEGATION) {
            result = unary();
        } else if(this.st.ttype == OPEN_SCOPE) {
            result = scope();
        } else if (this.st.ttype == StreamTokenizer.TT_WORD) {
            if (st.sval.equals(SIN) ||
                st.sval.equals(COS) ||
                st.sval.equals(EXP) ||
                st.sval.equals(NEG) ||
                st.sval.equals(LOG)) {

                result = unary();
            } else if(this.st.sval.equals(IF)) {
                result = conditional();

            
    
            } else if (this.st.sval.equals(FUNCTION)) {
                FunctionDeclaration func;
                if(functionParsingMode == true) {
                    throw new RuntimeException("Nested functions are not permitted");
                }
                this.st.nextToken();
                if (this.st.ttype == StreamTokenizer.TT_WORD) {
                    func = new FunctionDeclaration(this.st.sval);
                } else {
                    throw new SyntaxErrorException("expected '('");
                }
                this.st.nextToken();
                if (this.st.ttype != '(') {
                    throw new SyntaxErrorException("expected '('");
                }

                this.st.nextToken();
                while((this.st.ttype != ')')) {
                    func.addArg(identifier());
                    this.st.nextToken();
                    if(this.st.ttype == ',') {
                        this.st.nextToken();
                        continue;
                    } else if( this.st.ttype != ')'){
                        throw new SyntaxErrorException("expected ')'"); 
                    }
                }

                result = func;



            } else {
                result = identifier();

            }
        }  else {
            this.st.pushBack();
            result = number();
        }
        return result;
    }

    private SymbolicExpression scope() throws IOException {
        SymbolicExpression result;
        if(this.st.ttype == OPEN_SCOPE) {
            this.st.nextToken();
            result = new Scope(assignment());

            this.st.nextToken();
            if (this.st.ttype != CLOSE_SCOPE) {
                throw new SyntaxErrorException("expected '}'");
            }
        } else {
            throw new SyntaxErrorException("expected '{'");
        }

        return result;
    }

    private SymbolicExpression conditional() throws IOException {
        if(!this.st.sval.equals(IF)) {
            throw new RuntimeException("expected 'if'");
        }

        SymbolicExpression result;
        this.st.nextToken();

        SymbolicExpression lhs = expression();
        String op = "";
    
        this.st.nextToken();

        if (st.ttype == LT) {
            this.st.nextToken();
            op =""+LT ;
            if(st.ttype == ASSIGNMENT) {
                this.st.nextToken();
                op = ""+LTE;
            }
            
        } else if(st.ttype == GT) {
            this.st.nextToken();
            op = "" + GT;
            if(st.ttype == ASSIGNMENT) {
                this.st.nextToken();
                op = "" + GTE;
            }

        } else if(st.ttype == ASSIGNMENT) {
            this.st.nextToken();
            if(st.ttype == ASSIGNMENT) {
                this.st.nextToken();
                op = "" + EQUALS;
            } else {
                throw new RuntimeException("expected conditional operator");
            }
            
        } else {
            throw new RuntimeException("expected conditional operator");
        }

        SymbolicExpression rhs = expression();

        this.st.nextToken();
        SymbolicExpression ifstate = assignment();
        
        this.st.nextToken();
        if(this.st.ttype == StreamTokenizer.TT_WORD && !this.st.sval.equals(ELSE)) {
            throw new RuntimeException("expected 'else'");
        }

        this.st.nextToken();
        SymbolicExpression elsestate = assignment();


        if(op.equals(""+LT)) {
            result = new LT(lhs, rhs, ifstate, elsestate);
        } else if(op.equals(""+GT)) {
            result = new GT(lhs, rhs, ifstate, elsestate);
        } else if(op.equals(""+LTE)) {
            result = new LTE(lhs, rhs, ifstate, elsestate);
        } else if(op.equals(""+GTE)) {
            result = new GTE(lhs, rhs, ifstate, elsestate);
        } else if(op.equals(EQUALS)){
            result = new Equals(lhs, rhs, ifstate, elsestate);
        } else {
            throw new RuntimeException("expected conditional operator");
        }

        return result;
    }

    /**
     * Checks what type of Unary operation the token read is and
     * then continues with the expression that the operator holds
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression unary() throws IOException {
        SymbolicExpression result;
        int operationNeg = st.ttype;
        String operation = st.sval;
        this.st.nextToken();
        if (operationNeg == NEGATION || operation.equals(NEG)) {
            result = new Negation(primary());
        } else if (operation.equals(SIN)) {
            result = new Sin(primary());
        } else if (operation.equals(COS)) {
            result = new Cos(primary());
        } else if (operation.equals(LOG)) {
            result = new Log(primary());
        } else {
            result = new Exp(primary());
        }
        return result;
    }

    /**
     * Checks if the token read is a number - should always be a number in this method
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression,
     *         expected a number which is not present
     */
    private SymbolicExpression number() throws IOException {
        this.st.nextToken();
        if (this.st.ttype == StreamTokenizer.TT_NUMBER) {
            return new Constant(this.st.nval);
        } else {
            throw new SyntaxErrorException("Error: Expected number");
        }
    }
}