
package Common;

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

    public static void info(String context, String message) {
        log(Severity.INFO, context, message);
    }

    public static void warning(String context, String message) {
        log(Severity.WARNING, context, message);
    }

    public static void error(String context, String message) {
        log(Severity.ERROR, context, message);
    }

    public static void fatal(String context, String message) {
        log(Severity.FATAL, context, message);
    }
}
