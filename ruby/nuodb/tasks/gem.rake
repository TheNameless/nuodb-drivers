#
# Copyright (c) 2012, NuoDB, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of NuoDB, Inc. nor the names of its contributors may
#       be used to endorse or promote products derived from this software
#       without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL NUODB, INC. BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
# OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

require 'rubygems/package_task'
require 'hoe'

HOE = Hoe.spec 'nuodb' do
  self.author = ['NuoDB, Inc.']
  self.email = ['info@nuodb.com']
  self.need_tar = false
  self.need_zip = false

  spec_extras[:required_ruby_version] = Gem::Requirement.new('>= 1.8.6')

  spec_extras[:extensions] = ['ext/nuodb/extconf.rb']
  clean_globs << "tmp" << "lib/nuodb/nuodb.so"

  extra_dev_deps << ['rake-compiler', "~> 0.7.0"]
end

file "#{HOE.spec.name}.gemspec" => ['Rakefile', 'tasks/gem.rake'] do |t|
  puts "Generating #{t.name}"
  File.open(t.name, 'w') { |f| f.puts HOE.spec.to_yaml }
end

desc "Generate or update the standalone gemspec file for the project"
task :gemspec => ["#{HOE.spec.name}.gemspec"]
