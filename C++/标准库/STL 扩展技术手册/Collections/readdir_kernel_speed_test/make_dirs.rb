

require 'recls'

fe = Recls::stat(".")

thisDir	=	fe.path + Recls::pathNameSeparator

puts thisDir

(0 ... 1000).each { |i| File::new("#{thisDir}f#{i}", "w") }

