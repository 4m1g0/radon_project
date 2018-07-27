<template>
<div id="list-container">
  <div class="scroll" v-bind:style="{ height: customHeight*1.9 + 'px' }">
    
    <ul class="collapsible">
      <li v-for="(schedule, index) in schedules" :key="index">
        <ScheduleHeader class="collapsible-header" :schedule="schedule" :timerId="index"/>
        <ScheduleBody class="collapsible-body" :schedule="schedule" :timerId="index" />
      </li>
    </ul>
  </div>
</div>
</template>

<script>
import Service from './Service'
import ScheduleBody from './ScheduleBody'
import ScheduleHeader from './ScheduleHeader'

export default {
    name: 'schedules',
    props: [
      'customHeight'
    ],
    components: {
      ScheduleBody, ScheduleHeader
    },
    data(){
      return {
        
        schedules:[{"Arm":1,"Mode":0,"Time":"00:00","Window":0,"Days":[true,true,true,true,false,false,true],"Repeat":0,"Output":1,"Action":0},{"Arm":1,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":0,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":0,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":0,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":0,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":0,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":0,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":0,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":0,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":1,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":0,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":0,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":0,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":0,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0},{"Arm":0,"Mode":0,"Time":"00:00","Window":0,"Days":[false,false,false,false,false,false,false],"Repeat":0,"Output":1,"Action":0}],
      }
    },
    methods: {
      
      toggled(i){
        // send to the api this.schedules[index]
        if (this.schedules[i].Arm == 0)
          this.schedules[i].Arm = 1;
        else 
          this.schedules[i].Arm = 0;

        this.saveSchedule(i);
      },
      update(data){
        this.schedules = data;
        this.$emit('set_loading', false);
      }
    },
    mounted(){
      document.addEventListener('DOMContentLoaded', function() {
        var elems = document.querySelectorAll('.collapsible');
        // eslint-disable-next-line
        M.Collapsible.init(elems, {});
      });
      
      Service.getTimers(this.update);
    }
}
</script>

<style scoped>
.scroll{
  overflow-y: scroll; /*vertical scroll*/
}

.collapsible-header {
  justify-content:space-between;
}
</style>

