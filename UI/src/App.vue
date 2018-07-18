<template>
  <div id="app">
    <div v-if="loggedin" >
      <ul id="dropdown1" class="dropdown-content">
        <li><a href="#!" @click="changeSensor(3)">Materiales IV</a></li>
        <li><a href="#!" @click="changeSensor(4)">Física</a></li>
      </ul>
      <nav>
        <div class="nav-wrapper green">
          <a href="#!" class="brand-logo">Radon Monitor</a>
          <ul class="left">
            <li><a class="dropdown-trigger" href="#!" data-target="dropdown1">{{currentSensor==3?"Materiales IV":"Física"}}<i class="material-icons right">arrow_drop_down</i></a></li>
          </ul>
          <ul class="right logout">
            <li><button class="btn" @click="logout">Log Out</button></li>
          </ul>
          
        </div>
      </nav>
      <div class="container">
        <div class="row">
          <div class="col l6 m12"><Card contentComponent="RealtimeData" :title="realtimeDataTitle"/></div>
          <div class="col l6 m12"><!--<Card contentComponent="ModuleInfo" :title="moduleInfoTitle"/>--></div>
        </div>
        <div class="row">
          <div class="col l6 m12"><Card contentComponent="RadonHistory" :title="radonHistoryTitle"/></div>
          <div class="col l6 m12"><!--<Card contentComponent="Schedules" :title="schedulesTitle"/>--></div>
        </div>
      </div>
    </div>
    <div v-if="!loggedin">
      <nav>
        <div class="nav-wrapper green">
          <a href="#!" class="brand-logo">IoT Network</a>
        </div>
      </nav>
      <div class="container">
        <div class="row">
          <div class="col s6 offset-s3">
            <Card contentComponent="Login" :title="loginTitle"/>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import Card from './components/Card.vue'
import { serverBus } from './main';

export default {
  name: 'app',
  components: {
    Card
  },
  data(){
    return {
      currentSensor: this.$cookie.get('sensor'),
      realtimeDataTitle: '<i class="material-icons">info_outline</i> Real time data',
      radonHistoryTitle: '<i class="material-icons">multiline_chart</i> Radon History',
      powerHistoryTitle: '<i class="material-icons">history</i> Power History',
      moduleInfoTitle: '<i class="material-icons">info_outline</i> Module Info',
      schedulesTitle: '<i class="material-icons">timer</i> Schedules',
      loginTitle: 'Login',
      loggedin: this.$cookie.get('token') != null,
    }
  },
  mounted(){
    var elems = document.querySelectorAll('.dropdown-trigger');
    // eslint-disable-next-line
    M.Dropdown.init(elems, {});
  },
   created() {
    // Using the service bus
    serverBus.$on('login', () => {
      location.reload();
    });
  },
  methods: {
    logout(){
      this.$cookie.delete('token');
      this.loggedin = false;
    },
    changeSensor(id){
      this.currentSensor = id;
      this.$cookie.set('sensor', id);
      location.reload();
    }
  }
}
</script>

<style>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

.background {
  z-index: -100;
   position:fixed; 
    height:100%; 
    width:100%;
  background: #2C3E50;  /* fallback for old browsers */
  background: -webkit-linear-gradient(to bottom, #4CA1AF, #2C3E50);  /* Chrome 10-25, Safari 5.1-6 */
  background: linear-gradient(to bottom, #4CA1AF, #2C3E50); /* W3C, IE 10+/ Edge, Firefox 16+, Chrome 26+, Opera 12+, Safari 7+ */
}

html, body{
  height: 150%;
}
nav {
  margin-bottom: 20px;
}

.logout {
  margin-right: 15px;
}

@media only screen and (min-width: 993px) {
 .container {
  width:90%
 }
}
</style>
