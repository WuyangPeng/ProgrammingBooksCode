unique = {}
lines = 0
last = ''

ARGF.each_line do |line|
  lines += 1
  puts "Line: #{lines}, unique #{unique.size}" if (lines % 100000) == 0
  line.gsub!(/ .*$/, '')
  next if line == last
  unique[line] = 1
  last = line
end

puts "Unique fetchers: #{unique.size}"
