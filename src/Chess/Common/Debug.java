
package Chess.Common;

public class Debug {

    private Debug() {}

    public enum Severity {
        INFO,
        WARNING,
        ERROR,
        FATAL
    }

    public static void log(Severity severity, String context, String message) {
        String line = severity.toString() + ": " + context + " | " + message;
        System.out.println(line);

        if(severity == Severity.FATAL) {
            System.exit(-1);
        }
    }

    public static void fatal(String context, String message) {
        log(Severity.FATAL, context, message);
    }
}
