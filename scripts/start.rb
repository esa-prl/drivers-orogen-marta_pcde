require 'orocos'
require 'readline'
include Orocos


## Initialize orocos ##
Orocos.initialize

## Execute the task 'messages::Producer' ##
Orocos.run 'pcde::Task' => 'pcde' do
  ## Get the task context##
  driver = Orocos.name_service.get 'pcde'

  ## Configure the task
  driver.configure

  ## Start the task ##
  driver.start

  Readline::readline("Press Enter to exit\n") do
    end

end