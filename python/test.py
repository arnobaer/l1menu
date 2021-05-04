import l1menu
import sys

menu = l1menu.read_xml(sys.argv[1])

sys.stdout.write(l1menu.write_xml(menu))
