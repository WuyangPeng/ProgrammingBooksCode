counts = {}
counts.default = 0

$<.grep(/^From: .*<([^>]*)>\n$/) { counts[$1] += 1 }

descending = counts.keys.sort { |a, b| counts[b] <=> counts[a] }
descending.each { |from| puts "From: #{from}: #{counts[from]}" }
