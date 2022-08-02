require 'Time'

unique = {}
lines = 0
last = ''

# 81.27.128.143 - - [10/Dec/2006:07:00:03 -0800] "GET /ongoing/ongoing.atom HTTP/1.1" 304 - "-" "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1) Gecko/20061010 Firefox/2.0"

ARGF.each_line do |line|
  if line =~ %r{^([^S]+) - - \[(..)/(...)/(....):(..):(..):(..) .*GET /ongoing/When/\d\d\dx/(\d\d\d\d/\d\d/\d\d/[^ .]+) }
    who = $1
    t = Time.local($4, $3, $2, $5, $6, $7)
    puts "#{who} #{t.to_i} #{$8}"
    lines += 1
    STDERR.puts "Line: #{lines} @ #{t}" if (lines % 100000) == 0
  end
end



