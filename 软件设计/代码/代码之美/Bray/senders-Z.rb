counts = {}
counts.default = 0
linecount = 0

ARGF.each do |line|
  linecount += 1
  STDERR.puts "line: #{linecount}" if linecount % 100000 == 0
  counts[$1] += 1 if line =~ /^From: .*<([^>]*)>\n$/
end

descending = counts.keys.sort { |a, b| counts[b] <=> counts[a] }
descending.each { |from| puts "From: #{from}: #{counts[from]}" }
