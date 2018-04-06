from cmd import Cmd

class myShell( Cmd ):
    prompt = '(hello)'
    doc_header = 'Available commands:'

    def __init__( self ):
        Cmd.__init__( self )
        print "Command myShell Intialized"

    def precmd( self, line ):
        print "Ran precmd"
        return line

    def do_show_version( self, arg ):
        'Print version information'
        print "Version 1.0"

    def do_exit( self, arg ):
        print "Exiting.."
        return True


if __name__ == "__main__":
    obj = myShell()
    obj.cmdloop()
