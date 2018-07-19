<template>
  <div class="card">
    <div class="card-content">
      <div class="card-title grey-text text-darken-4" v-html="title">
      </div>
       <div class="progress" v-show="loading">
          <div class="indeterminate"></div>
      </div>
      
      <div class="card-body" id="card-body" ref="cardBody">
        <component :is="contentComponent" @set_loading="setLoading" :customHeight="computedHeight"></component>
        <div v-show="loading" class="spinner">
          <div class="preloader-wrapper large active">
            <div class="spinner-layer spinner-green-only">
              <div class="circle-clipper left">
                <div class="circle"></div>
              </div><div class="gap-patch">
                <div class="circle"></div>
              </div><div class="circle-clipper right">
                <div class="circle"></div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import RealtimeData from './RealtimeData'
import RadonHistory from './RadonHistory'
import DailyStats from './DailyStats'
import Login from './Login'

export default {
  name: 'card',
  props: [
    'contentComponent',
    'title'
  ],
  components: {
    RealtimeData,
    RadonHistory,
    DailyStats,
    Login
  },
  data() {
    return {
      loading: true,
      width: 0,
    }
  },
  methods: {
    setLoading(value){
      this.loading = value;
    },
    handleResize(){
      this.width = this.$refs.cardBody.clientWidth;
      // eslint-disable-next-line
      console.log(this.width);
    }
  },
  mounted(){
    this.handleResize();
    window.addEventListener('resize', this.handleResize)
  },
  computed: {
    computedHeight(){
      return this.width/3;
    }
  }
}

</script>

<style scoped>
.card-title{
  border-bottom: 1px solid #cfcfcf;
}

.spinner{
  height: 100px;
  margin: auto;
}
</style>


